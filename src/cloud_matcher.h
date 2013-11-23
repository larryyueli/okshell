/*
 * cloud_matcher.h
 * The matcher that matches with the cloud
 *
 *  Created on: 2013-11-22
 *      Author: Larry Yueli Zhang
 */

#ifndef CLOUD_MATCHER_H_
#define CLOUD_MATCHER_H_

#include "local_matcher.h" // TEMP

namespace okshell
{
namespace detail
{
typedef LocalMatchResultType    CloudMatchResultType;
typedef LocalMatchEntry         CloudMatchEntry;
typedef LocalMatcher            CloudMatcher;
typedef LocalMatchResult        CloudMatchResult;

} // end namespace detail
} // end namespace okshell

#endif /* CLOUD_MATCHER_H_ */
