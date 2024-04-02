#pragma once

#include "hal/oaqm_filesystem.h"

class SDFileSystemHal : public FileSystemHal {
  public:
    SDFileSystemHal() {};
    virtual bool initialize();
    ~SDFileSystemHal() {};
};