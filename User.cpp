#include <User.h>

User::User(std::string usr, std::string pwd, std::string fname, std::string lname, std::string eml, std::string tkn){
//declare variables for this constructor
	username = usr;
	password = pwd;
	firstName = fname;
	lastName = lname;
	email = eml;
	token = tkn;
}

User::User(const User& other){ //will copy the constructor variables
	username = other.username;
	password = other.password;
	firstName = other.firstName;
	lastName = other.lastName;
	email = other.email;
	token = other.token;
}

std::ostream& operator <<(std::ostream& os, const User& u){
	
	os<< u.username << ":"<< u.password<<u.firstName<< u.lastName << u.email<< u.token;
	return os;
}

bool User::operator ==(const User& other) const {

	return username == other.username && 
	password == other.password &&
	firstName == other.firstName && 
	lastName == other.lastName &&
	email == other.email &&
	token == other.token;
	}

bool User::operator !=(const User& other) const {
	return username != other.username && 
	password != other.password &&
	firstName != other.firstName && 
	lastName != other.lastName &&
	email != other.email &&
	token != other.token;
} //!(*this) == other) ; would be better because the == is already checking the above 

std::string User::getUsername() const {
	return username;
}

std::string User::getPassword() const {
	return password;
}

std::string User::getFirstName() const {
	return firstName;
}

std::string User::getLastName() const {
	return lastName;
}

std::string User::getEmail() const {
	return email;
}

std::string User::getToken() const {
	return token;
}

