#include "Channel.hpp"
#include "irc.hpp"

Channel::Channel()
{
#if SHOW_CONSTRUCTOR
	std::cout << "Channel default constructor" << std::endl;
#endif
	//this is prohibited
}

Channel::~Channel()
{
#if SHOW_CONSTRUCTOR
	std::cout << "Channel default destructor" << std::endl;
#endif
}

Channel::Channel(std::string name, Client& owner) :  _owner(&owner), _nbOfClients(0), _name(name)
{
#if SHOW_CONSTRUCTOR
	std::cout << "Channel string Client constructor" << std::endl;
#endif
}

Channel::Channel(const Channel &source)
{
#if SHOW_CONSTRUCTOR
	std::cout << "Channel copy constructor" << std::endl;
#endif
	*this = source;
}

Channel &Channel::operator=(const Channel &rhs)
{
#if SHOW_CONSTRUCTOR
	std::cout << "Channel = overload" << std::endl;
#endif
	this->_owner = rhs._owner;
	this->_nbOfClients = rhs._nbOfClients;
	this->_name = rhs._name;
	return (*this);
}

bool Channel::operator<(const Channel &rhs) const
{
	return (this->_name < rhs._name);
}

std::string	Channel::getName() const
{
	return (this->_name);
}

void	Channel::updateChannelName(std::string name)
{
	this->_name = name;
}

int		Channel::isUserConnected(Client& user)
{
	std::map<int, Client*>::iterator it = this->_connectedClients.find(user.getSocketFD());
	if (it != this->_connectedClients.end())
		return (CONNECTED);
	return (NOT_CONNECTED);
}

void	Channel::addUserToChannel(Client& user)
{
	if (this->isUserConnected(user) == NOT_CONNECTED)
	{
		this->_connectedClients.insert(std::make_pair(user.getSocketFD(), &user));
		this->_nbOfClients++;
		user.joinChannel(*this);
	}
}

/* returns the number of connected clients after the operation to delete chan if empty*/
int		Channel::removeUserFromChannel(Client& user)
{
	if (this->isUserConnected(user) == CONNECTED)
	{
		this->_nbOfClients--;
		user.quitChannel(*this);

		std::map<int, Client*>::iterator clientIterator = this->_connectedClients.find(user.getSocketFD());
		if (clientIterator != this->_connectedClients.end())
			this->_connectedClients.erase(clientIterator);
	}
	return (this->_nbOfClients);
}