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

#define BIN_TX_QUEUE_SIZE 4
#define HEX_TX_QUEUE_SIZE 4
#define CAN_TX_QUEUE_SIZE 2

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

	Command();
	Command(uint8_t id, uint8_t to, uint8_t from, uint8_t size);

	void setHeader(Entry header);
	Entry getHeader() const;

	Command& operator=(const Command& command);
};

template<uint8_t N>
class Queue {
public:
	Queue();

	inline uint8_t size() const { return size_; };
	inline const Command& first() const { return buf[read_ptr_]; };
	inline const Command& last() const { return buf[(write_ptr_ - 1) % N]; };

//	bool push(Command& command);
//	bool push();
//	bool pop(Command& command);
//	bool pop();
//
	bool push(Command& command) {
		if (size_ == N) return false;

		buf[write_ptr_] = command;

		return push();
	}
	bool push() {
		if (size_ == N) return false;

		write_ptr_++;
		if (write_ptr_ >= N) write_ptr_ = 0;
		size_++;

		return true;
	}
	bool pop(Command& command) {
		if (size_ == 0) return false;

		command = first();

		return pop();
	}
	bool pop() {
		if (size_ == 0) return false;

		read_ptr_++;
		if (read_ptr_ >= N) read_ptr_ = 0;
		size_--;

		return true;
	}

private:
	Command buf[N];
	uint8_t size_;
	uint8_t read_ptr_;
	uint8_t write_ptr_;
};


template<uint8_t TXQ>
class Channel {
public:
	Queue<TXQ> tx;
	Command rx;

	Channel();

	inline void cancelSending() { sending_ = -1; tx.pop(); };

	inline bool isReceiving() { return receiving_ != -1; };
	inline bool isSending() { return tx.size() > 0; };

protected:
	int8_t receiving_;
	int8_t sending_;
};

class BinaryChannel: public Channel<BIN_TX_QUEUE_SIZE> {

};

class HexChannel: public Channel<HEX_TX_QUEUE_SIZE> {
public:
	HexChannel();

	bool receive(const uint8_t* data, uint8_t len);

	uint8_t send(uint8_t* data, uint8_t& len);
private:
	uint8_t rx_buf_[12];
	uint8_t rx_buf_count_;
};

class CANChannel: public Channel<CAN_TX_QUEUE_SIZE> {
public:
	CANChannel();

	bool receive(uint8_t std_id, const uint8_t* data, uint8_t len);

	uint8_t send(uint8_t& std_id, uint8_t* data, uint8_t& len);
};


#endif /* COMMAND_HPP_ */
