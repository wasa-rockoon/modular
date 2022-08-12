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
#define MAX_ENTRIES 16


union Payload {
	uint8_t bytes[4];
	uint32_t uint;
	int32_t int_;
	float float_;
};


struct Entry {
    uint8_t type;
    union Payload payload;

    void set(uint8_t type);
    void set(uint8_t type, const uint8_t* bytes);
    void set(uint8_t type, int32_t value);
    void set(uint8_t type, uint32_t value);
    void set(uint8_t type, float value);

	uint8_t encode(uint8_t* buf) const;
	uint8_t encodeHex(uint8_t* buf) const;
	bool decode(const uint8_t* buf, uint8_t len);
	uint8_t decodeHex(const uint8_t* buf);
};

struct Command {
	uint8_t id;
	uint8_t to;
	uint8_t from;
	uint8_t size;
	Entry entries[MAX_ENTRIES];

	void setHeader(Entry header);
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
	Command tx;
	Command rx;

	bool receive(uint8_t std_id, const uint8_t* data, uint8_t len);

	uint8_t send(uint8_t& std_id, uint8_t* data, uint8_t& len);
	void cancelSending();

	bool isReceiving();
	bool isSending();

private:
	int8_t receiving = -1;
	int8_t sending = -1;
};


#endif /* COMMAND_HPP_ */
