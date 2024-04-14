#include <iostream>
#include <memory>

#include "Record.h"
#include "StagedProvider.h"

using namespace std;

/**
  * Class constructor that takes in Staging Config
  * @param cfg staging config
 */
StagedProvider::StagedProvider(unique_ptr<StagingConfig> &stagingCfg) {
    cfg = std::move(stagingCfg);

    storageOffset = cfg->storageStartOffset;
    storageRemaining = cfg->recordCount * Record::getRecordSize();

    stagingOffset = 0;
    stagingRemaining = 0;

    bufferOffset = 0;
    bufferRemaining = 0;
    totalRecordsReturned = 0;
}

/**
   * Gets the next record from from the (staging) chunk of HDD
   * Places the next HDD chunk into SDD for reading
   * @returns a pointer to the next record or a null pointer if a next record doesn't exist
 */
shared_ptr<Record> StagedProvider::next() {
    if (totalRecordsReturned >= cfg->recordCount) return nullptr;

    int recordSize = Record::getRecordSize();
    unique_ptr<uint8_t[]> data = make_unique<uint8_t[]>(recordSize);

    int recordRemaining = recordSize;
    int recordOffset = 0;

    while (true) {
        if (recordRemaining < 1) {
            totalRecordsReturned++;
            return make_shared<Record>(data);
        }

        if (bufferRemaining < 1) {
            if (stagingRemaining < 1) {
                int sizeToRead = cfg->bufferLength + cfg->stagingLength;
                if(storageRemaining < sizeToRead) sizeToRead = storageRemaining;
                int count = cfg->storage->read(storageOffset,  cfg->transferBuffer, sizeToRead);
                if(count != sizeToRead) {
                    cerr <<"Error in staged provider\n";
                    exit(1);
                }
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
                    cfg->staging->write(cfg->stagingStartOffset, cfg->transferBuffer, sizeToRead - cfg->bufferLength);
                    stagingOffset = 0;
                    stagingRemaining = sizeToRead - cfg->bufferLength;
                    bufferOffset = 0;
                    bufferRemaining = cfg->bufferLength;
                }
            } else {
                // there is data available in the staging area, lets read it.
                int sizeToRead = cfg->bufferLength;
                if(stagingRemaining < sizeToRead) sizeToRead = stagingRemaining;
                int count = cfg->staging->read(cfg->stagingStartOffset + stagingOffset, cfg->buffer, sizeToRead);
                if(count != sizeToRead) {
                    cerr <<"Error in staged provider\n";
                    exit(1);
                }
                stagingOffset += sizeToRead;
                stagingRemaining -= sizeToRead;
                bufferOffset = 0;
                bufferRemaining = sizeToRead;
            }
        }

        int sizeToCopy = recordRemaining;
        if(bufferRemaining < sizeToCopy) sizeToCopy = bufferRemaining;
        memcpy(data.get() + recordOffset, cfg->buffer + bufferOffset, sizeToCopy);
        recordOffset += sizeToCopy;
        recordRemaining -= sizeToCopy;
        bufferOffset += sizeToCopy;
        bufferRemaining -= sizeToCopy;
    }
}
