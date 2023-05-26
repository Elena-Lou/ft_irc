#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <map>

class Client;
class Channel
{
	public:
		~Channel();
		Channel(const Channel &source);
		Channel &operator=(const Channel &rhs);
		bool operator<(const Channel &rhs) const;
		Channel(std::string name, Client& owner);

		void	updateChannelName(std::string);

		/* getters */
		std::string getName() const;

		/* users handler */
		int		isUserConnected(Client& user);
		int		removeUserFromChannel(Client& user);
		void	addUserToChannel(Client&);

	private:
		Channel();
		Client*				_owner;
		int					_nbOfClients;
		std::string			_name;
		std::map<int, Client*>	_connectedClients;
	protected:
};

#endif