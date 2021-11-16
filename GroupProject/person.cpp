#include "person.h"

Person::Person() {
}

Person::Person(std::string ID, std::string jobTitle, std::string email, std::string lastName, std::string firstName, std::string phoneNo, std::string skills, std::string country)
{
	this->ID = ID;
	this->jobTitle = jobTitle;
	this->email = email;
	this->lastName = lastName;
	this->firstName = firstName;
	this->phoneNo = phoneNo;
	this->skills = skills;
	this->country = country;
}

std::string Person::getID() {
	return ID;
}

std::string Person::getjobTitle()
{
	return jobTitle;
}

std::string Person::getEmail()
{
	return email;
}

std::string Person::getLastName()
{
	return lastName;
}

std::string Person::getFirstName()
{
	return firstName;
}

std::string Person::getPhoneNo()
{
	return phoneNo;
}

std::string Person::getSkills()
{
	return skills;
}

std::string Person::getCountry()
{
	return country;
}
