#ifndef MODE_HPP
# define MODE_HPP

# include "ACommand.hpp"
# include "irc.hpp"

class Client;
class Server;
class Mode : public ACommand
{
	public:
		Mode(Server &server, Client & author, std::string rawInput);
		Mode(const Mode &source);
		Mode &operator=(const Mode &rhs);
		~Mode();

	protected:
	private:
		Mode();
		void	execute();
		void	error(int) const;
		void	confirm() const;

		bool	isAPossibleChannelName(std::string name);
		void	checkValidCmd();

		void	invite();
		void	topic();
		void	channelKey();
		void	channelOp();
		void	channelLimit();

		Channel *_targetChannel;
		Client	*_targetClient;
};

#endif
