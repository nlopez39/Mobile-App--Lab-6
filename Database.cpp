#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>
#include <Database.h>

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out){
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

bool Database::checkFile(std::string path){
	namespace fs = boost::filesystem;
	
	fs::path full_path( fs::initial_path<fs::path>() );
    full_path = fs::system_complete( fs::path( path ) );
	return fs::is_regular_file(full_path);
}

void Database::readDb(){
	std::ifstream inFile(db_path);

	std::string line;

	while (inFile >> line){
		std::vector<std::string> items;
		tokenize(line, ':', items);
		std::string username = items[0];
		std::string password = items[1];
		std::string firstName = items[2];
		std::string lastName = items[3];
		std::string email = items[4];
		std::string token = items[5];
		User* user = new User(username, password, firstName, lastName, email, token);
		storage.insert({username, user});
	}
}

Database::Database(){
	persistent = false;
}

Database::Database(std::string filepath){
	persistent = true;
	if (!checkFile(filepath)){
		std::ofstream fs(filepath);
	}
	db_path = filepath;

	readDb();
}

Database::Database(const Database& other){
	persistent = other.persistent;
	db_path = other.db_path;
	for (auto itr : other.storage){
		std::string key = itr.first;
		User* user = itr.second;
		storage.insert({key, new User(*user)});
	}
}

bool Database::hasKey(std::string key){
	return storage.find(key) != storage.end();
}

User* Database::get(std::string key){
	auto pos = storage.find(key);
	if (pos != storage.end()){
		return pos->second;
	}
}

void Database::write(std::string key, User* value){
	storage.insert({key, value});
	if (persistent){
		std::ofstream outfile;

		outfile.open(db_path, std::ios_base::app);
		outfile << value->getUsername() << ":" << value->getPassword() << ":" << value->getFirstName() << ":" << value->getLastName() << ":" << value->getEmail() << ":" << value->getToken() << std::endl;
	} 
}

Database::~Database(){
	for (auto itr : storage){
		delete itr.second;
	}
}

bool Database::operator == (const Database& other) const {

	auto one = storage;
	auto two = other.storage;

	for (auto itr : one){
		std::string key = itr.first;
		auto pos = two.find(key);
		if (pos == two.end()){
			return false;
		}
		else{
			User* value = itr.second;
			if (*value != *(pos->second)){
				return false;
			}
		}
	}

	for (auto itr : two){
		std::string key = itr.first;
		auto pos = one.find(key);
		if (pos == one.end()){
			return false;
		}
		else{
			User* value = itr.second;
			if (*value != *(pos->second)){
				return false;
			}
		}
	}
	return true;
}
bool Database::operator !=(const Database& other) const {
	return !(*this == other);
}

std::ostream& operator <<(std::ostream& os, const Database& db){
	for (auto itr: db.storage){
		os << itr.first << " - " << *itr.second << std::endl;
	}
	return os;
}
