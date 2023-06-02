
# include "ACommand.hpp"
# include "User.hpp"
# include "Client.hpp"

User::User() : ACommand()
{
	/*this is forbidden */
}

User::~User()
{
}

User::User(Server &server, Client &author, std::string rawInput) : ACommand(server, author, rawInput)
{
	this->execute();
}

User::User(const User &source)
{
	*this = source;
}

User &User::operator=(const User &rhs)
{
	this->_cmd = rhs._cmd;
	this->_author = rhs._author;
	return (*this);
}

void User::execute() const
{
	if (this->_cmd.size() != 2)
	{
		error(ERR_NONICKNAMEGIVEN);
		return ;
	}
	std::string newName = this->_cmd[1];
	for (unsigned int i = 0; i < newName.size(); i++)
	{
		if (!isalpha(newName[i]))
		{
			error(ERR_ERRONEUSNICKNAME);
			return ;
		}
	}

	if (!this->_server->isUserConnected(newName))
	{
		error(ERR_NICKNAMEINUSE);
		return ;
	}

	//No condition for ERR_NICKCOLLISION not required by subject
	std::string message;
	message += this->_author->getNickname() + " changed his nickname to " + newName + ".\r\n";
	this->confirm();
}

void User::error(int errorCode) const
{
	std::stringstream errorMessage;
	errorMessage << ":" << this->_server->getHostname() << " " << errorCode << " "
	<< this->_author->getNickname();
	switch (errorCode)
	{
		case ERR_NONICKNAMEGIVEN:
			errorMessage << " :" << ERR_NONICKNAMEGIVEN_MSG << CRLF;
			break;
		case ERR_ERRONEUSNICKNAME:
			errorMessage << this->_cmd[1] << " :" << ERR_ERRONEUSNICKNAME_MSG << CRLF;
			break;
		case ERR_NICKNAMEINUSE:
			errorMessage << this->_cmd[1] << " :" << ERR_NICKNAMEINUSE_MSG << CRLF;
			break;
		default:
			std::cerr << "Error: Unrecognised error code." << std::endl;
			break;
	}
	this->_author->writeBuffer += errorMessage.str();
}

void	User::confirm() const
{
	std::stringstream replyMessageBuilder;
	replyMessageBuilder << ":" << this->_author->getFullName() << this->_cmd[0] << " "  << this->_cmd[1];
	std::string replyMessage = replyMessageBuilder.str();
	this->_server->broadcastAllClients(replyMessage);
}
