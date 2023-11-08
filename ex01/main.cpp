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
#include <Serializer.hpp>

int main()
{
    Data	myData;
    myData.myInt = 123;
    myData.myStr = "hello world";

    std::cout << "myInt: " << Serializer::deserialize(Serializer::serialize( &myData ))->myInt << std::endl;
    std::cout << "myStr: " << Serializer::deserialize(Serializer::serialize( &myData ))->myStr << std::endl;
}
