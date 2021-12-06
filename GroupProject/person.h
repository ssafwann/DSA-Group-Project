/*
	A class used to represent a person object(includes 8 attributes)
*/
#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
	std::string ID;
	std::string jobTitle;
	std::string email;
	std::string lastName;
	std::string firstName;
	std::string phoneNo;
	std::string skills;
	std::string country;

public:
	Person();
	Person(std::string ID, std::string jobTitle, std::string email, std::string lastName,std::string firstName, std::string phoneNo, std::string skills, std::string country);
	std::string getID();
	std::string getjobTitle();
	std::string getEmail();
	std::string getLastName();
	std::string getFirstName();
	std::string getPhoneNo();
	std::string getSkills();
	std::string getCountry();
};

#endif // !PERSON_H