/**
 * @file common.h
 * @author
 * @brief
 * @version 0.1
 * @date 2022-02-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_INTERNAL_COMMON_H_
#define ARA_COM_INTERNAL_COMMON_H_

#include <sstream>

namespace ara
{
    namespace com
    {
        namespace SKELETON
        {

            class LogStream
            {
            public:
                explicit LogStream(bool essential, int level);

                virtual ~LogStream();

                template <typename T>
                LogStream &operator<<(const T &value)
                {
                    if (m_essential)
                    {
                        m_sstream << value;
                    }

                    return *this;
                }

            private:
                bool m_essential;
                std::stringstream m_sstream;
                int m_level;
            };

            class Logger
            {
            public:
                Logger() {}
                virtual ~Logger() {}

                LogStream LogFatal() noexcept;

                LogStream LogError() noexcept;

                LogStream LogWarn() noexcept;

                LogStream LogInfo() noexcept;

                LogStream LogDebug() noexcept;

                LogStream LogVerbose() noexcept;
            };

            Logger &logger();

            std::string CODE_POS(std::string file, std::string function, int line);

            void MakeTmpDir();

        } // namespace internal
    }     // namespace com
} // namespace ara

#endif // ARA_COM_INTERNAL_COMMON_H_
