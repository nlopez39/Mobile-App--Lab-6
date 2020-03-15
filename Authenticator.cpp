#include <fstream>
#include <iostream>
#include <boost/uuid/uuid.hpp>            
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>         
#include <Authenticator.h>

Authenticator::Authenticator(Database* db){
	this->db = db;


}

Authenticator::Authenticator(const Authenticator& other){
	this->db = other.db;
}

ucm::json Authenticator::authenticate(std::string username, std::string password){
	ucm::json response;
	response["success"] = false;
	if(db ->hasKey(username)){ //checks if username exists
		User* userCopy = db -> get(username); //if it does then it is placed in a userCopy 
	if(userCopy -> getPassword() == password)//checks if the password is true in user.cpp
		response["success"] = true;
		response["token"] = userCopy -> getToken();
		//if true then user gets token because the input was a success
	}

	
	return response;
}
	
ucm::json Authenticator::signup(std::string usr, std::string pwd, std::string fname, std::string lname, std::string email){

	ucm::json response;
	if(db -> hasKey(usr) == true){
		response["success"] = false;
		response["message"] = "Username is already taken";
	}else{

	
//if username exists then output username is already taken 

	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	std::stringstream s;
	s << uuid;
	std::string token = s.str();

	User* copyUser = new User(usr,pwd,fname,lname, email, token); //makes a copy of all the information 
		db -> write(usr,copyUser); //all the info from userCopy
		response["success"] = true;

	
	}
	return response;
}

ucm::json Authenticator::details(std::string username, std::string token){
	
	ucm::json response;
	User* userCopy = db -> get(username);

	if(userCopy -> getToken() ==token && userCopy ->getUsername() == username){
		response["success"] = true;
		response["First Name"] = userCopy -> getFirstName();
		response["Last Name"] = userCopy -> getLastName();
		//response["Info"] = info; //set response to all info 
	}else{
	response["success"] = false;
	}
	return response;
};
