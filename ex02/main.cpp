/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobu <arobu@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:57:53 by arobu             #+#    #+#             */
/*   Updated: 2023/07/03 18:48:14 by arobu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <Base.hpp>

void	leaks() {
	system("leaks Base");
}

int main()
{
 	unsigned int seed = static_cast<unsigned int>(std::time(0)) ^ static_cast<unsigned int>(getpid());
	std::srand(seed);
	Base *base;
	atexit(leaks);
	for (int i = 0; i < 10; ++i) {
		base = generate();
		identify(base);
		identify(*base);
		delete base;
	}
}
