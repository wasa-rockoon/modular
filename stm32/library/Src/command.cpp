/*
 * command.cpp
 *
 *  Created on: Jun 25, 2022
 *      Author: yuuki.fj
 */

#include <command.hpp>
#include <stdio.h>
#include <stdlib.h>


void Entry::set(uint8_t type) {
	this->type = type, payload.uint = 0;
}

void Entry::set(uint8_t type, const uint8_t* bytes) {
	this->type = type;
	for (int i = 0; i < 4; i++) payload.bytes[i] = bytes[i];
}

void Entry::set(uint8_t type, int32_t value) {
	this->type = type;
	payload.int_ = value;
}

void Entry::set(uint8_t type, uint32_t value) {
	this->type = type;
	payload.uint = value;
}

void Entry::set(uint8_t type, float value) {
	this->type = type;
	payload.float_ = value;
}

uint8_t Entry::encode(uint8_t* buf) const {
    if (payload.int_ == 0) {
    	buf[0] = type || 0b10000000;
    	return 1;
    }
    else {
    	buf[0] = type;
        for (int i = 0; i < 4; i++) buf[i + 1] = payload.bytes[i];
        return 5;
    }
}

bool Entry::decode(const uint8_t* buf, uint8_t len) {
	type = buf[0] & 0b01111111;
	if (len == 5 && !(buf[0] & 0b10000000)) {
		for (int i = 0; i < 4; i++) payload.bytes[i] = buf[1 + i];
		return true;
	}
	else if (len == 1 && (buf[0] & 0b10000000)) {
		return true;
	}
	else return false;
}

uint8_t Entry::encodeHex(uint8_t* buf) const {
    uint8_t data[5];
    uint8_t len;

    if (payload.int_ == 0) {
        data[0] = type || 0b10000000;
        len = 1;
    }
    else {
    	data[0] = type;
        for (int i = 0; i < 4; i++) data[i + 1] = payload.bytes[i];
    	len = 5;
    }

    for (int i = 0; i < len; i++) {
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
    buf[len * 2] = '\0';
    return len * 2;
}

uint8_t Entry::decodeHex(const uint8_t* buf) {
    char *err = nullptr;
    uint8_t data[5];
    char hex[3];

    hex[0] = buf[0];
    hex[1] = buf[1];
    hex[2] = '\0';
    data[0] = (uint8_t)strtol(hex, &err, 16);
    if (*err != '\0') return 0;

    type = data[0] & 0b01111111;

    if (buf[0] & 0b1000000) {
    	return 2;
    	payload.int_ = 0;
    }
    else {
		for (int i = 1; i < 5; i++) {
			hex[0] = buf[2 * i];
			hex[1] = buf[2 * i + 1];
			hex[2] = '\0';
			data[i] = (uint8_t)strtol(hex, &err, 16);
		}
		if (*err != '\0') return false;
		for (int i = 0; i < 4; i++) payload.bytes[i] = data[1 + i];
		return 10;
    }
}

void Command::setHeader(Entry header) {
	id = header.payload.bytes[0];
	to = header.payload.bytes[1];
	from = header.payload.bytes[2];
	size = header.payload.bytes[3];
}

Entry Command::getHeader() const {
	Entry header;
	header.type = 0;
	header.payload.bytes[0] = id;
	header.payload.bytes[1] = to;
	header.payload.bytes[2] = from;
	header.payload.bytes[3] = size;
	return header;
}


bool CANChannel::receive(uint8_t std_id, const uint8_t* data, uint8_t len) {

	Entry entry;
	if (!entry.decode(data, len)) return false;

	// Start receiving new command
	if (entry.type == 0) {
		rx.setHeader(entry);
		receiving = 0;
	}
	// Cancel receiving
	else if (receiving == -1 || std_id != rx.id) {
		receiving = -1;
		return false;
	}
	// Continue receiving
	else {
		rx.entries[receiving] = entry;
		receiving++;
	}

	if (receiving == rx.size) {
		receiving = -1;
		return true;
	}
	else return false;
}

uint8_t CANChannel::send(uint8_t& std_id, uint8_t* data, uint8_t& len) {
	std_id = tx.id;
	if (receiving != -1) {
		len = 0;
		return tx.size;
	}
	if (sending == -1) {
		Entry header = tx.getHeader();
		len = header.encode(data);
		sending = 0;
	}
	else {
		len = tx.entries[sending].encode(data);
		sending++;
	}
	int remains = tx.size - sending;
	if (remains == 0) sending = -1;
	return remains;
}

void CANChannel::cancelSending() {
	sending = -1;
}

bool CANChannel::isReceiving() {
	return receiving != -1;
}

bool CANChannel::isSending() {
	return sending != -1;
}
