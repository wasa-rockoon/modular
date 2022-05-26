/*
 * comm.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: yuuki.fj
 */

#include <command.h>
#include <stdio.h>
#include <stdlib.h>


void encode(Entry entry, uint8_t* buf) {
    buf[0] = entry.type;
    for (int i = 0; i < 4; i++) buf[i + 1] = entry.payload.bytes[i];
}

bool decode(Entry* entry, const uint8_t* buf) {
	entry->type = buf[0];
	for (int i = 0; i < 4; i++) entry->payload.bytes[i] = buf[1 + i];

	return true;
}

void encodeHex(Entry entry, uint8_t* buf) {
    uint8_t data[5] = {entry.type};
    for (int i = 0; i < 4; i++) data[i + 1] = entry.payload.bytes[i];

    for (int i = 0; i < 5; i++) {
        char hex[3];
        sprintf(hex, "%X", data[i]);
        if (data[i] < 16) {
            buf[i*2]   = '0';
            buf[i*2+1] = hex[0];
        }
        else {
            buf[i*2]   = hex[0];
            buf[i*2+1] = hex[1];
        }
    }
    buf[10] = '\0';
}

bool decodeHex(Entry* entry, const uint8_t* buf) {
    char *err = NULL;
    uint8_t data[5];
    for (int i = 0; i < 5; i++) {
        char hex[3];
        hex[0] = buf[2 * i];
        hex[1] = buf[2 * i + 1];
        hex[2] = '\0';
        data[i] = (uint8_t)strtol(hex, &err, 16);
    }
    if (*err != '\0') return false;

    entry->type = data[0];
    for (int i = 0; i < 4; i++) entry->payload.bytes[i] = data[1 + i];

    return true;
}

Command* readHex(HexChannel* c, const uint8_t* buf, int len) {
	for (int i = 0; i < len; i++) {
		if (c->read_buf_count >= READ_BUFFER_SIZE) break;
		c->read_buf[c->read_buf_count] = buf[i];
		c->read_buf_count++;
	}

	// printf("read %.*s\n", c->read_buf_count, c->read_buf);

	bool complete = false;
	int n = 0;
	while (n < (int)c->read_buf_count - 10) {

		bool abort = false;
		int i;
		for (i = 0; i < 10; i++) {
			if (c->read_buf[n + i] == '\n') {
				abort = true;
			}
		}
		if (abort) {
			n += i + 1;
			break;
		}

		Entry entry;
		bool success = decodeHex(&entry, c->read_buf + n);

		if (!success) n = c->read_buf_count;
		else {
			n += 10;
			while (c->read_buf[n] == '\n') n++;
			if (entry.type == 0x00) { // New command
				c->reading.id = entry.payload.bytes[0];
				c->reading.to = entry.payload.bytes[1];
				c->reading.from = entry.payload.bytes[2];
				c->reading.size = entry.payload.bytes[3];
				if (c->reading.size > MAX_ENTRIES) {
					c->reading.size = MAX_ENTRIES;
				}
				c->cursor_read = 0;
			}
			else if (c->cursor_read >= 0) { // Continue receiving
				if (c->cursor_read >= MAX_ENTRIES) {
					complete = true;
					c->cursor_read = -1;
					break;
				}
				c->reading.entries[c->cursor_read] = entry;
				c->cursor_read++;
			}
			if (c->cursor_read >= c->reading.size) {
				complete = true;
				c->cursor_read = -1;
				break;
			}
		}
	}

	for (int i = 0; i + n < c->read_buf_count; i++) {
		c->read_buf[i] = c->read_buf[i + n];
	}
	c->read_buf_count -= n;

	if (complete) return &(c->reading);
	else return NULL;
}

int writeHex(HexChannel* c, const Command* command, uint8_t* buf, int* len) {

	Entry entry;

	if (c->cursor_write == 0) {
		entry.type = 0x00;
		entry.payload.bytes[0] = command->id;
		entry.payload.bytes[1] = command->to;
		entry.payload.bytes[2] = command->from;
		entry.payload.bytes[3] = command->size;
	}
	else {
		entry = command->entries[c->cursor_write - 1];
	}

	encodeHex(entry, buf);

	if (c->cursor_write == command->size) {
		c->cursor_write = 0;
		buf[10] = '\n';
		*len = 11;
		return 0;
	}

	c->cursor_write++;

	*len = 10;
	return command->size + 1 - c->cursor_write;
}

int alloc(CANChannel* c) {
	for (unsigned i = 0; i < MAX_STREAMS; i++) {
		if (c->cursor_read[i] == c->readings[i].size) return i;
	}

	unsigned free_command = 0;
	unsigned max_time = 0;
	for (unsigned i = 0; i < MAX_STREAMS; i++) {
		unsigned time = c->clock - c->last_updated[i];
		if (time > max_time) {
			free_command = i;
			max_time = time;
		}
	}
	return free_command;
}
int find(CANChannel* c, uint8_t unique) {
	for (unsigned i = 0; i < MAX_STREAMS; i++) {
		if (c->unique_receive[i] == unique) return i;
	}
	return -1;
}


Command* readCAN(CANChannel* c, const uint8_t* buf) {
	c->clock++;

	uint8_t unique = buf[0] | (buf[1] << 8) | (buf[2] << 16);

	Entry entry;
	decode(&entry, buf + 3);

	// printf("%c\n", entry.type);

	if (entry.type == 0x00) { // New command
		int i = alloc(c);
		c->readings[i].id = entry.payload.bytes[0];
		c->readings[i].to = entry.payload.bytes[1];
		c->readings[i].from = entry.payload.bytes[2];
		c->readings[i].size = entry.payload.bytes[3];
		c->last_updated[i] = c->clock;
		c->cursor_read[i] = 0;
		c->unique_receive[i] = unique;

		if (c->readings[i].size == 0) return &c->readings[i];

		return NULL;
	}
	int i = find(c, unique);
	if (c->cursor_read[i] >= 0) { // Continue receiving
		if (i < 0) return NULL;
		c->readings[i].entries[c->cursor_read[i]] = entry;
		c->cursor_read[i]++;
		//printf("%d %d %d\n", i, c->readings[i].size, c->cursor_read[i]);
		if (c->cursor_read[i] >= c->readings[i].size) {
			c->cursor_read[i] = -1;
			return &c->readings[i];
		}
		c->last_updated[i] = c->clock;

		return NULL;
	}
	return NULL;
}

int writeCAN(CANChannel* c, const Command* command, uint8_t* buf) {
	c->clock++;

	Entry entry;

	if (c->cursor_write == 0) {
		c->unique_send = (c->clock * command->id * command->to * command->from) % 0xFFFFFF;
		entry.type = 0x00;
		entry.payload.bytes[0] = command->id;
		entry.payload.bytes[1] = command->to;
		entry.payload.bytes[2] = command->from;
		entry.payload.bytes[3] = command->size;
	}
	else {
		int i = c->cursor_write - 1;
		if (i < 0) {
			i = 0;
		}
		if (i >= MAX_ENTRIES) {
			c->cursor_write = 0;
			return 0;
		}
		entry = command->entries[i];
	}

	buf[0] = c->unique_send & 0xFF;
	buf[1] = (c->unique_send >> 8) & 0xFF;
	buf[2] = (c->unique_send >> 16) & 0xFF;
	encode(entry, buf + 3);

	if (c->cursor_write >= command->size) {
		c->cursor_write = 0;
		return 0;
	}

	c->cursor_write++;

	return command->size + 1 - c->cursor_write;
}

void printCommand(Command* command) {
	if (!command) return;
	printf("command id:'%c'(%d) to:'%c'(%d) from:'%c'(%d) size:%d\n",
			command->id, command->id, command->to, command->to, command->from, command->from, command->size);
	for (int n = 0; n < command->size; n++) {
		printf("  '%c'(%d): %d\n",
			   command->entries[n].type, command->entries[n].type, command->entries[n].payload.int_);
	}
}



