#include "../AssetAbstract.h"

namespace GameAssets
{
	logger::LogStream LogLine( logger::LogLevel level )
	{
		class myLog
		{
		private:
			logger::Log m_Log;
			logger::FilePolicy m_LogFile;
		public:
			myLog() : m_Log( &m_LogFile )
			{
				m_LogFile.Open( "Assets.log", true );
				m_Log.Line( logger::_INFO ) << "ASSET LOGGING SESSION STARTED";
			}
			~myLog()
			{
				m_Log.Line( logger::_INFO ) << "ASSET LOGGING SESSION ENDED";
			}
			inline logger::LogStream Line( logger::LogLevel level )
			{
				return m_Log.Line( level );
			}
		};
		static myLog Log;
		return Log.Line( level );
	}
}