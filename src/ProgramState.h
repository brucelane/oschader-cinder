#pragma once

#include <memory>
#include <string>
#include <map>
#include <functional>

class ProgramFactory;
class Program;

class ProgramState;
typedef std::shared_ptr<ProgramState> ProgramStateRef;

class ProgramState {
public:
	void setProgram(std::string id, std::string name, std::function<std::shared_ptr<Program>()>);
	void clearProgram(std::string id);
	std::shared_ptr<Program> getProgram(std::string id);
	
private:
	std::map<std::string, std::pair<std::string, std::shared_ptr<Program>>> mState;
};