/*
 * command.hpp
 *
 *  Created on: Jun 25, 2022
 *      Author: yuuki.fj
 */

#ifndef COMMAND_HPP_
#define COMMAND_HPP_



#include <stdint.h>
#include <stdbool.h>

#define NUM_STREAMS 4


union Payload {
	uint8_t bytes[4];
	uint32_t uint;
	int32_t int_;
	float float_;
};


struct Entry {
    uint8_t type;
    union Payload payload;


	void encode(uint8_t* buf) const;
	void encodeHex(uint8_t* buf) const;
	bool decode(const uint8_t* buf);
	bool decodeHex(const uint8_t* buf);
};

struct Command {
	uint8_t id;
	uint8_t to;
	uint8_t from;
	uint8_t size;
	Entry* entries;

	Command(Entry header);
	~Command();

	Entry getHeader() const;
};


class ReceivingCommand {
public:
	Command* command;
	uint32_t std_id;
	uint32_t recently_used;

	bool start(uint32_t std_id, Entry header, uint32_t time);
	bool addEntry(Entry entry, uint32_t time);
	void abort();

	bool isFree();

private:
	uint8_t count;
};


class HexChannel {

};

class CANChannel {
public:
	Command* receive(uint8_t std_id, const uint8_t* data);

	void send(const Command* command, void (*send_fun)(const uint8_t* data, uint8_t len));

private:
	uint32_t time;
	ReceivingCommand receivings[NUM_STREAMS];
};


#endif /* COMMAND_HPP_ */
