#ifndef _AR_H_
#define _AR_H_

namespace Ar 
{
   int create(char *buf, int buf_len);
    int rewind(int fd);
    int datalen(int fd);
    int remain(int fd);
    char* getptr(int fd);
    int test();
    char* malloc(int len); 
    int free(int fd);
    int writebuf(int fd, const char* buf, int len);
    int writelstr(int fd, const char* str);
    int writelstr(int fd, const char* str, int len);
    int writeint8(int fd, int8 val);
    int writeint16(int fd, int16 val);
    int writeint32(int fd, int32 val);
    int writeint64(int fd, int64 val);
    int skip(int fd, int len);
    int readbuf(int fd, char* str, int len);
    int readlstr(int fd, char* str, int len);
    int readuint8(int fd);
    int readint8(int fd);
    int readint16(int fd);
    int readint32(int fd);
    int readint64(int fd);

    int lreadstr(lua_State *L);
    int lreadlstr(lua_State *L);
};

#endif
