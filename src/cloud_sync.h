/*
 * cloud_sync.h
 * The class used for syncing with cloud.
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#ifndef CLOUD_SYNC_H_
#define CLOUD_SYNC_H_

#include "common_defs.h"

namespace okshell
{
namespace detail
{
class CloudSync
{
public:
    CloudSync() {}
    
public:
    // sync with cloud
    // return whether sync was successful
    bool sync() const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(CloudSync);
};

} // end namespace detail
} // end namespade okshell

#endif /* CLOUD_SYNC_H_ */
