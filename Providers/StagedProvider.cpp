#include "StagedProvider.h"
#include <assert.h>

StagedProvider::StagedProvider(StagingConfig cfg):storage("test"), staging("test") {
    this->recordSize = cfg.recordSize;
    this->recordCount = cfg.recordCount;
    this->storageStartOffset = cfg.storageStartOffset;
    this->stagingStartOffset = cfg.stagingStartOffset;
    this->stagingLength = cfg.stagingLength;
    this->bufferPtr = cfg.bufferPtr;
    this->bufferStartOffset = cfg.bufferStartOffset;
    this->bufferLength = cfg.bufferLength;
    this->transferBuffer = cfg.transferBuffer;
    this->transferStartOffset = cfg.transferStartOffset;

    assert(cfg.transferLength >= bufferLength + stagingLength);
    //TODO: dereference buffer pointer
   // assert(cfg.bufferStartOffset + cfg.bufferLength <= cfg.bufferPtr.length);

    storageRemaining = recordCount * (long)recordSize;
}
