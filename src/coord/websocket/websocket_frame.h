#pragma once 


#include "coord/coordx.h"
#include "coord/memory/type.h"
#include <uv.h>

namespace coord {//tolua_export
class Coord;

namespace websocket {//tolua_export

/*

 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-------+-+-------------+-------------------------------+
|F|R|R|R| opcode|M| Payload len |    Extended payload length    |
|I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
|N|V|V|V|       |S|             |   (if payload len==126/127)   |
| |1|2|3|       |K|             |                               |
+-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
|     Extended payload length continued, if payload len == 127  |
+ - - - - - - - - - - - - - - - +-------------------------------+
|                               |Masking-key, if MASK set to 1  |
+-------------------------------+-------------------------------+
| Masking-key (continued)       |          Payload Data         |
+-------------------------------- - - - - - - - - - - - - - - - +
:                     Payload Data continued ...                :
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
|                     Payload Data continued ...                |
+---------------------------------------------------------------+

*/
class Server;
class Agent;

enum websocket_frame_type {
    websocket_frame_type_close = 8,
    websocket_frame_type_Text = 1,
    websocket_frame_type_binary = 2,
    websocket_frame_type_ping = 9,
    websocket_frame_type_pong = 10,
};

struct websocket_frame_header {
    uint8_t opcode:4;
    uint8_t rsv:3;
    uint8_t fin:1;
    uint8_t payloadLen:7;
    uint8_t mask:1;
};

class Frame : public coord::RcObject {//tolua_export
RC_CLASS(Frame);
public:
    Frame(Coord* coord, Agent* agent);
    virtual ~Frame();
public:
    size_t parse(char* data, size_t len);
public:
    Agent*                  agent;
    Server*                 server;
    int                     sessionId;  
    Coord*                  coord;
    uint64_t                payloadLen;
    char*                   payload;
    uint32_t                headerLen;
    uint64_t                frameLen;
    websocket_frame_header  header;
    bool                    isComplete; 
};//tolua_export

Frame* newWebSocketFrame(Coord* coord, Agent* agent);

}//tolua_export
}//tolua_export


