
#include <iostream>
#include <memory>
#include <algorithm> // for std::min

#include "Record.h"
#include "StagedProvider.h"

using namespace std;


StagedProvider::StagedProvider(unique_ptr<StagingConfig> stagingCfg) {
    cfg = std::move(stagingCfg);
    storageOffset = 0;
    storageRemaining = cfg->recordCount * Record::getRecordSize();
    stagingOffset = 0;
    stagingRemaining = 0;
    bufferOffset = 0;
    bufferRemaining = 0;
    nextRecord = 0;
}

/**
 * @return a pointer to the next record or a null pointer if all records have been generated
 */
shared_ptr<Record> StagedProvider::next() {
    if (nextRecord >= cfg->recordCount) return nullptr;
    nextRecord++;

    int recordRemaining = Record::getRecordSize();
    uint8_t data[recordRemaining];
    uint8_t* dataptr = &data[0];

    int recordOffset = 0;
    while (true) {
        if (recordRemaining < 1) {
            return make_shared<Record>(&data[0]);
        }

        if (bufferRemaining < 1) {
            if (stagingRemaining < 1) {
                int sizeToRead = cfg->bufferLength + cfg->stagingLength;
                if(storageRemaining < sizeToRead) sizeToRead = storageRemaining;
                cfg->storage->read( cfg->storageStartOffset + storageOffset,  cfg->transferBuffer, sizeToRead);
                storageOffset += sizeToRead;
                storageRemaining -= sizeToRead;

                if (sizeToRead <= cfg->bufferLength) {
                    // this must be the final chunk on the HDD.
                    // It is small enough to fit in the buffer.
                    // move pointers to point to correct destination in destination and source
                    memcpy(cfg->buffer, cfg->transferBuffer, sizeToRead);
                    stagingOffset = 0;
                    stagingRemaining = 0;
                    bufferOffset = 0;
                    bufferRemaining = sizeToRead;
                } else {
                    // we need to put the beginning of the transfer buffer into our buffer,
                    // and the rest of the data needs to be written to the staging area
                    // move pointers to point to correct destination in destination and source
                    memcpy(cfg->buffer, cfg->transferBuffer, cfg->bufferLength);
                    cfg->staging->write(cfg->stagingStartOffset, cfg->transferBuffer, 0, sizeToRead - cfg->bufferLength);
                    stagingOffset = 0;
                    stagingRemaining = sizeToRead - cfg->bufferLength;
                    bufferOffset = 0;
                    bufferRemaining = cfg->bufferLength;
                }
            } else {
                // there is data available in the staging area, lets read it.
                int sizeToRead = cfg->bufferLength;
                if(stagingRemaining < sizeToRead) sizeToRead = stagingRemaining;
                cfg->staging->read(cfg->stagingStartOffset + stagingOffset, cfg->buffer, sizeToRead);
                stagingOffset += sizeToRead;
                stagingRemaining -= sizeToRead;
                bufferOffset = 0;
                bufferRemaining = sizeToRead;
            }
        }

        int sizeToCopy = recordRemaining;
        if(bufferRemaining < sizeToCopy) sizeToCopy = bufferRemaining;
        memcpy(dataptr + recordOffset, cfg->buffer + bufferOffset, sizeToCopy);
        recordOffset += sizeToCopy;
        recordRemaining -= sizeToCopy;
        bufferOffset += sizeToCopy;
        bufferRemaining -= sizeToCopy;
    }
}
