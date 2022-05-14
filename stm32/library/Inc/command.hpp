/*
 * comm.h
 *
 *  Created on: Apr 29, 2022
 *      Author: yuuki.fj
 */

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <stdint.h>
#include <stdbool.h>

#define MAX_ENTRIES 64

union Payload {
	uint8_t bytes[4];
	uint32_t uint;
	int32_t int_;
	float float_;
};


class Entry {
public:
    uint8_t type;
    Payload payload;

    void encode(uint8_t* buf);
    void encodeHex(uint8_t* buf);

    bool decode(const uint8_t* buf);
    bool decodeHex(const uint8_t* buf);
};

class Command {
public:
	uint8_t id;
	uint8_t to;
	uint8_t from;
	uint8_t size;
	Entry entries[MAX_ENTRIES];

private:
	uint8_t received_size;
};

class Channel {
public:
	bool readCANPacket(const uint8_t* buf, Command& command);
	int writeCANPacket(uint8_t* buf, Command& command);
	bool readHex(const uint8_t* buf, Command& command);
	int writeHex(uint8_t* buf, Command& command);

private:

};



#define TYPE_ALL 0

typedef struct {
    uint8_t id;
    uint8_t seq;
    uint8_t type;
    uint8_t index;
    uint32_t payload;
} Message;

//
//typedef void (*Callback)(const Message<uint32_t>& payload);
//
//class Comm {
//private:
//    uint8_t id;
//
//    uint8_t seq = 0;
//
//    uint8_t callback_types[MAX_CALLBACKS];
//    Callback callbacks[MAX_CALLBACKS];
//    uint8_t callback_count = 0;
//
//public:
//
//    Comm(uint8_t id): id(id) {};
//
//    void nextSequence() {seq++;};
//
//    // Receiving
//    template <typename T>
//        void listen(uint8_t type,
//                    void (*callback)(const Message<T>& message)) {
//        listen(type, reinterpret_cast<Callback>(callback));
//    }
//
//    // Sending
//    void send(uint8_t type, uint8_t index);
//    template <typename T>
//        void send(uint8_t type, uint8_t index, const T& payload) {
//        return send(type, index, reinterpret_cast<const uint32_t>(&payload));
//    }
//
//    bool receive(String &str);
//
//private:
//    void listen(uint8_t type,
//                void (*callback)(const Message<uint32_t>& message));
//    void send(uint8_t type, uint8_t index, const uint32_t payload);
//
//protected:
//    virtual void writeLine(char* str) = 0;
//};


#endif /* COMMAND_HPP_ */
