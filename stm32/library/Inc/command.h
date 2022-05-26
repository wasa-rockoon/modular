/*
 * comm.h
 *
 *  Created on: Apr 29, 2022
 *      Author: yuuki.fj
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_ENTRIES 16
#define READ_BUFFER_SIZE 400
#define MAX_STREAMS 4

union Payload {
	uint8_t bytes[4];
	uint32_t uint;
	int32_t int_;
	float float_;
};


typedef struct {
    uint8_t type;
    union Payload payload;
} Entry;

void encode(Entry entry, uint8_t* buf);
void encodeHex(Entry entry, uint8_t* buf);

bool decode(Entry* entry, const uint8_t* buf);
bool decodeHex(Entry* entry, const uint8_t* buf);


typedef struct {
	uint8_t id;
	uint8_t to;
	uint8_t from;
	uint8_t size;
	Entry entries[MAX_ENTRIES];
} Command;

void printCommand(Command* command);

typedef struct {
	uint8_t read_buf[READ_BUFFER_SIZE];
	unsigned read_buf_count;
	Command reading;
	int cursor_read;
	int cursor_write;
} HexChannel;

Command* readHex(HexChannel* c, const uint8_t* buf, int len);
int writeHex(HexChannel* c, const Command* command, uint8_t* buf, int* len);

typedef struct {
	unsigned clock;

	Command readings[MAX_STREAMS];
	int cursor_read[MAX_STREAMS];
	unsigned last_updated[MAX_STREAMS];
	unsigned unique_receive[MAX_STREAMS];

	int cursor_write;
	unsigned unique_send;
} CANChannel;

Command* readCAN(CANChannel* c, const uint8_t* buf);
int writeCAN(CANChannel* c, const Command* command, uint8_t* buf);



#endif /* COMMAND_H_ */
