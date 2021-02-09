#pragma once

#include <bitset>
#include <cstdint>

using namespace std;

static const int bit_length = 128;
static const int end_length = 24;

struct BitBuffer
{
	bitset<bit_length> data; 
	int						pos;  
	int						count;

	BitBuffer();
	bool getBit();
	uint8_t getByte();
	void putBit(bool b);
	void putByte(uint8_t b);
};

struct ByteBuffer
{
	uint8_t *data;   
	uint64_t pos;    
	uint64_t length; 
	uint64_t totalLength; 
	ByteBuffer();
	uint8_t getByte();
	void putByte(uint8_t b);
	void setData(uint8_t *buffer, int len);
};

class BitOutputStream
{
public:
	void putBit(bool b);
	void putBit(bool b, int num);
	void setBuffer(uint8_t *buffer, int len);
	void resetBuffer();
	uint64_t freeLength();
	bool flush();
	uint64_t getTotalCodeLength()
	{
		return bytes.pos;
	}

private:
	BitBuffer bits;
	ByteBuffer bytes;
};

enum BufferState
{
	BUFFER_EMPTY, 
	BUFFER_END_SYMBOL, 
	BUFFER_LACK,
	BUFFER_ENGOUGH
};

class BitInputStream
{
public:
	bool getBit();
	void setBuffer(uint8_t *buffer, int len);
	BufferState check();
private:
	BitBuffer bits;
	ByteBuffer bytes;
};
