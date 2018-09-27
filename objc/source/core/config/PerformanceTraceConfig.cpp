/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <WCDB/PerformanceTraceConfig.hpp>
#include <WCDB/String.hpp>

namespace WCDB {

PerformanceTraceConfig::PerformanceTraceConfig(const Notification &notification)
: Config()
, m_identifier(String::formatted("PerformanceTrace-%p", this))
, m_notification(notification)
{
}

bool PerformanceTraceConfig::invoke(Handle *handle)
{
    handle->setNotificationWhenPerformanceTraced(m_identifier, m_notification);
    return true;
}

bool PerformanceTraceConfig::uninvoke(Handle *handle)
{
    handle->setNotificationWhenPerformanceTraced(m_identifier, nullptr);
    return true;
}

ShareablePerformanceTraceConfig::ShareablePerformanceTraceConfig()
: PerformanceTraceConfig(nullptr)
{
}

void ShareablePerformanceTraceConfig::setNotification(const Notification &notification)
{
    LockGuard lockGuard(m_lock);
    m_notification = notification;
}

bool ShareablePerformanceTraceConfig::invoke(Handle *handle)
{
    SharedLockGuard lockGuard(m_lock);
    return PerformanceTraceConfig::invoke(handle);
}

} //namespace WCDB