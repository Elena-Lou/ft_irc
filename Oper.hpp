#ifndef OPER_HPP
# define OPER_HPP

# include "ACommand.hpp"
# include "irc.hpp"

class Client;
class Server;
class Oper : public ACommand
{
	public:
		Oper(Server & server, Client & author, std::string rawInput);
		~Oper();

		Oper(Oper const & src);
		Oper &operator=(Oper const & rhs);

		void	execute();
		void	error(int) const;
		void	confirm() const;
	protected:
	private:
		Oper();
};

#endif