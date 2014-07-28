#include "com.h"

#include <unistd.h> //for (file) read() and write()
#include <fcntl.h> //needed for (file) open()
#include "logging.h"

namespace gparse {

Com::Com(const std::string &file) : _fd(open(file.c_str(), O_RDWR | O_NONBLOCK)) {
}

bool Com::tendCom() {
	char chr;
	while (read(_fd, &chr, 1) == 1) { //read all characters available on serial line.
		if (chr == '\n') {
			_parsed = Command(_pending);
			if (!NO_LOG_M105 || !_parsed.isM105()) {
				LOG("command: %s\n", _pending.c_str());
			}
			_pending = "";
			return true;
		} else if (chr != '\r') {
			_pending += chr;
		}
	}
	return false;
}

Command Com::getCommand() const {
	return _parsed;
}

void Com::reply(const Command &response) const {
	std::string resp = response.toGCode();
	if (!NO_LOG_M105 || !_parsed.isM105()) {
		LOG("response: %s", resp.c_str());
	}
	/*ssize_t res = */ write(_fd, resp.c_str(), resp.length());
}


}