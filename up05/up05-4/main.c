#include <sys/stat.h>

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

enum
{
    OFFSET_USR = 6,
    OFFSET_GRP = 3,
};

int
myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (!task->uid) {
        return 1;
    }

    if (task->uid == stb->st_uid) {
        return ((stb->st_mode >> OFFSET_USR & access) == access);
    }

    int count = task->gid_count;
    unsigned gid = stb->st_gid;
    for (int i = 0; i < count; i++) {
        if (task->gids[i] == gid) {
            return ((stb->st_mode >> OFFSET_GRP & access) == access);
        }
    }

    return ((stb->st_mode & access) == access);
}
