#include <iostream>

class CircularQueue {
public:
    CircularQueue();
    CircularQueue(CircularQueue const& );
    char *getHead();
    char *getStart();
    char *getEnd();
    unsigned int getReadCount();
    unsigned int getWriteCount();

private:
    const char *m_head;
    char *m_start;
    char *m_end;
    unsigned int m_readCount;
    unsigned int m_writeCount;
}

char *CircularQueue::getHead()
{
    return m_head;
}

char *CircularQueue::getStart()
{
    return m_start;
}

char *CircularQueue::getEnd()
{
    return m_end;
}

unsigned int CircularQueue::getReadCount()
{
    return m_readCount;
}

unsigned int CircularQueue::getWriteCount()
{
    return m_writeCount;
}

CircularQueue::CircularQueue(CircularQueue const& arg)
    :m_head(arg.getHead())
    ,m_start(arg.getStart())
    ,m_end(arg.getEnd())
    ,m_readCount(arg.getReadCount())
    ,m_writeCount(arg.getWriteCount())
{
}
