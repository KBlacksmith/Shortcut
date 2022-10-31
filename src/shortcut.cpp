#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>

void trimmer(std::string *arg){
    auto start = 0;
    auto end = arg->length();
    if(arg->compare("")){
        while (arg->substr(start, end-start).starts_with(" ") || arg->substr(start, end-start).starts_with("\t"))
        {
            start++;
        }
        while (arg->substr(start, end-start).ends_with(" ") || arg->substr(start, end-start).starts_with("\t"))
        {
            end--;
        }
        arg->assign(arg->substr(start, end-start));
    }
}

void to_lower_case(std::string * arg){
	for(int i = 0; i < arg->length(); i++){
		arg->at(i) = std::tolower(arg->at(i));
	}
}

void create_desktop_file(
	std::string * name, std::string * exec, std::string * path, 
	std::string * icon, std::string * terminal
){
	std::ofstream desktop_file(*name+".desktop");
	desktop_file << "[Desktop Entry]\nName=" << name->data() << "\nExec=" << exec->data();
	desktop_file << "\nPath=" << path->data() << "\n";
	if(icon->empty()){
		desktop_file << "#";
	}
	desktop_file << "Icon=" << icon->data() << "\nTerminal=" << terminal->data() << "\nType=Application\n";
	desktop_file.close();
}

int main(int argc, char * argv[]){
	std::string name, exec, path, icon, terminal, accept;
	std::cout << "Shortcut Desktop Entry Manager\n";
	while (name.empty())
	{
		std::cout << "\nName=";
		std::getline(std::cin, name);
		trimmer(&name);
	}
	while (exec.empty())
	{
		std::cout << "Exec=";
		std::getline(std::cin, exec);
		trimmer(&exec);
	}
	while (path.empty())
	{
		std::cout << "Path=";
		std::getline(std::cin, path);
		trimmer(&path);
	}
	std::cout << "Icon=";
	std::getline(std::cin, icon);
	trimmer(&icon);
	do{
		std::cout << "Terminal=";
		std::getline(std::cin, terminal);
		trimmer(&terminal);
		to_lower_case(&terminal);
	} while(terminal.compare("true") != 0 && terminal.compare("false") != 0);
	while (accept.empty())
	{
		system("clear");
		std::cout << "[Desktop Entry]\nName=" << name << "\nExec=" << exec << "\nPath=" << path;
		std::cout << "\nIcon=" << icon << "\nTerminal=";
		if (terminal.compare("true") == 0){
			std::cout << "true\n";
		}
		else{
			std::cout << "false\n";
		}
		std::cout << "Is this information correct? Y/n: ";
		std::getline(std::cin, accept);
		trimmer(&accept);
		to_lower_case(&accept);
		if(accept.compare("y") == 0 || accept.compare("yes") == 0){
			create_desktop_file(&name, &exec, &path, &icon, &terminal);
			std::cout << "Desktop Entry created succesfully!\n";
		}
		else if(accept.compare("n") == 0 || accept.compare("no") == 0){
			std::cout << "Program aborted.\n";
		}
		else{
			accept.assign("");
		}
	}
	
	return 0;
}

