#include "StagedProvider.h"
#include <assert.h>

StagedProvider::StagedProvider(StagingConfig cfg):storage("test"), staging("test") {
    this->recordSize = cfg.recordSize;
    this->recordCount = cfg.recordCount;
    this->storageStartOffset = cfg.storageStartOffset;
    this->stagingStartOffset = cfg.stagingStartOffset;
    this->stagingLength = cfg.stagingLength;
    this->buffer = cfg.buffer;
    this->bufferStartOffset = cfg.bufferStartOffset;
    this->bufferLength = cfg.bufferLength;
    this->transferBuffer = cfg.transferBuffer;
    this->transferStartOffset = cfg.transferStartOffset;

    assert(cfg.transferLength >= bufferLength + stagingLength);
    assert(cfg.bufferStartOffset + cfg.bufferLength <= sizeOf(cfg.buffer));

    storageRemaining = recordCount * (long)recordSize;
}
