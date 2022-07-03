/*
 * command.cpp
 *
 *  Created on: Jun 25, 2022
 *      Author: yuuki.fj
 */

#include <command.hpp>
#include <stdio.h>
#include <stdlib.h>

void Entry::encode(uint8_t* buf) const {
    buf[0] = type;
    for (int i = 0; i < 4; i++) buf[i + 1] = payload.bytes[i];
}

bool Entry::decode(const uint8_t* buf) {
	type = buf[0];
	for (int i = 0; i < 4; i++) payload.bytes[i] = buf[1 + i];

	return true;
}

void Entry::encodeHex(uint8_t* buf) const {
    uint8_t data[5] = { type };
    for (int i = 0; i < 4; i++) data[i + 1] = payload.bytes[i];

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

bool Entry::decodeHex(const uint8_t* buf) {
    char *err = nullptr;
    uint8_t data[5];
    for (int i = 0; i < 5; i++) {
        char hex[3];
        hex[0] = buf[2 * i];
        hex[1] = buf[2 * i + 1];
        hex[2] = '\0';
        data[i] = (uint8_t)strtol(hex, &err, 16);
    }
    if (*err != '\0') return false;

    type = data[0];
    for (int i = 0; i < 4; i++) payload.bytes[i] = data[1 + i];

    return true;
}

Command::Command(Entry header) {
	id = header.payload.bytes[0];
	to = header.payload.bytes[1];
	from = header.payload.bytes[2];
	size = header.payload.bytes[3];
	entries = (Entry *)malloc(sizeof(Entry) * size);
}


Command::~Command() {
	free(entries);
}

Entry Command::getHeader() const {
	Entry header;
	header.payload.bytes[0] = id;
	header.payload.bytes[1] = to;
	header.payload.bytes[2] = from;
	header.payload.bytes[3] = size;
	return header;
}

bool ReceivingCommand::start(uint32_t std_id, Entry header, uint32_t time) {
	recently_used = time;

	this->std_id = std_id;
	count = 0;
	command = new Command(header);

	return command->size == 0;
}

bool ReceivingCommand::addEntry(Entry entry, uint32_t time) {
	recently_used = time;

	command->entries[count] = entry;
	count++;
	if (command->size == count) {
		std_id = 0;
		count = 0;
		return true;
	}
	return false;
}

void ReceivingCommand::abort() {
	free(command);
	std_id = 0;
	count = 0;
}

inline bool ReceivingCommand::isFree() {
	return std_id == 0;
}

Command* CANChannel::receive(uint8_t std_id, const uint8_t* data) {

	time++;

	Entry entry;
	if (!entry.decode(data)) return nullptr;

	// Add entry to receiving command
	for (int i = 0; i < NUM_STREAMS; i++) {
		if (receivings[i].std_id == std_id) {
			if (receivings[i].addEntry(entry, time)) return receivings[i].command;
			else return nullptr;
		}
	}

	// Start receiving new command

	uint8_t lru = 0;
	uint32_t lru_time = 0;
	for (int i = 0; i < NUM_STREAMS; i++) {

		if (receivings[i].isFree()) {
			if (receivings[i].start(std_id, entry, time)) return receivings[i].command;
			else return nullptr;
		}

		if (time - receivings[i].recently_used > lru_time) {
			lru = i;
			lru_time = time - receivings[i].recently_used;
		}
	}

	receivings[lru].abort();

	if (receivings[lru].start(std_id, entry, time)) return receivings[lru].command;
	else return nullptr;
}

void CANChannel::send(const Command* command, void (*send_fun)(const uint8_t* data, uint8_t len)) {
	uint8_t buf[5];

	Entry header = command->getHeader();
	header.encode(buf);
	send_fun(buf, 5);

	for (int n = 0; n < command->size; n++) {
		command->entries[n].encode(buf);
		send_fun(buf, 5);
	}
}
