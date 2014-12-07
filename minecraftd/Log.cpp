Log::Log ()
{
	Log("/var/log/minecraftd.log", Level::WARN);
}

Log::Log(std::string path, Log::Level mask)
{
	this->path = path;
	this->mask = mask;
	this->file.open(path, std::fstream::out | std::fstream::trunc);
	if (!this->file.is_open()) throw new LogException(__FILE__, __LINE__);
	this->state = Log::State::OPEN;
}

Log::~Log()
{
	if (this->file.is_open())
	{
		this->file.close();
		this->state = State::CLOSED;
	}
}

void Log::write (Log::Level level, std::string msg)
{
	// Throw exception if log file isn't open.
	if (this->state != Log::State::OPEN) throw new LogException(__FILE__, __LINE__);
	// Only write to the log if level is greater than or equal to mask.
	if (level >= this->mask)
	{
		// Get timestamp
		std::tm *time = std::localtime(std::time(0));
		std::string timeStamp = "[" + time->tm_year + "-" + time->tm_mon + "-" + time->tm_mday +
			" " + time->tm_hour + ":" + time->tm_min + ":" + time->tm_sec + "] ";
		
		// Get levelstamp
		std::string levelStamp;
		switch(level)
		{
			case Log::Level::DEBUG:
				levelStamp = " [DEBUG] ";
				break;
			case Log::Level::INFO:
				levelStamp = " [INFO] ";
				break;
			case Log::Level::WARN:
				levelStamp = " [WARN] ";
				break;
			case Log::Level::ERROR:
				levelStamp = " [ERROR] ";
				break;
			case Log::Level::FATAL:
				levelStamp = " [FATAL] ";
				break;
			default:
				levelStamp = " [] ";
				break;
		}
		// Write log message
		this->file << timeStamp << levelStamp << msg << std::endl;
	}
}