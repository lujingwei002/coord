#include "coord/builtin/platform.h"
#include "coord/coord.h"
#include <uv.h>
#include<sys/file.h> // flock
#include <fcntl.h> // open


namespace coord {
    namespace path {
        bool IsAbsolutePath(const char* path) {
            return path[0] == '/';
        }

        std::string PathJoin(const std::string& p1, const std::string& p2) {
            return p1 + "/"  + p2;
        }

        std::string DirName(const std::string& path) {
            auto pos = path.rfind("/");
            if (pos != std::string::npos) {
                return path.substr(0, pos);
            } else {
                return path;
            }
        }

        int RealPath(const std::string& path, std::string& realPath) {
            uv_fs_t req;
            int err = uv_fs_realpath(&coorda->loop, &req, path.c_str(), nullptr);
            if (err) {
                return err;
            }
            realPath.assign((char*)req.ptr);
            return 0;
        }

        int MakeDir(const std::string& path, int mode) {
            uv_fs_t req;
            int err = uv_fs_mkdir(&coorda->loop, &req, path.c_str(), mode, nullptr);
            if (err) {
                return err;
            }
            return 0;
        }

        bool Exists(const std::string& path) {
            uv_fs_t req;
            int err = uv_fs_stat(&coorda->loop, &req, path.c_str(), nullptr);
            if (err) {
                return false;
            }
            return true;
        }

        int FileLock(const std::string& path) {
            int fd = open(path.c_str(), O_RDWR|O_CREAT, 0755);
            if (fd < 0) {
                return 1;
            }
            if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
                return 2;
            }
            return 0;
        }

        int RemoveDir(const std::string& path) {
            uv_fs_t req;
            int err = uv_fs_rmdir(&coorda->loop, &req, path.c_str(), nullptr);
            if (err) {
                coorda->CoreLogError("RemoveDir failed, path='%s', err='%s'", path.c_str(), uv_strerror(err));
                return err;
            }
            return 0;
        }

        int Unlink(const std::string& path) {
            uv_fs_t req;
            int err = uv_fs_unlink(&coorda->loop, &req, path.c_str(), nullptr);
            if (err) {
                coorda->CoreLogError("Unlink failed, path='%s', err='%s'", path.c_str(), uv_strerror(err));
                return err;
            }
            return 0;
        }

        int RemoveDirRecursive(const std::string& path) {
            uv_fs_t req;
            uv_dirent_t ent;
            uv_fs_scandir(&coorda->loop, &req, path.c_str(), 0, NULL);
            int err;
            while(uv_fs_scandir_next(&req, &ent) != UV_EOF) {
                if (ent.type == UV_DIRENT_DIR) {
                    std::string newPath = PathJoin(path, ent.name);
                    err = RemoveDirRecursive(newPath);
                    if (err) {
                        return err;
                    }
                } else {
                    std::string newPath = PathJoin(path, ent.name);
                    err = Unlink(newPath);
                    if (err) {
                        return err;
                    }
                }
            }
            return RemoveDir(path);
        }



        
    }
}
