/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:18:59 by dabae             #+#    #+#             */
/*   Updated: 2024/04/08 17:58:59 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int ft_put_char(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_put_str(char *str)
{
    int i;

    i = 0;
    if (!str)
        str = "(null)";
    while (str[i])
    {
        ft_put_char(str[i]);
        i++;
    }
    return (i);
}

int ft_put_nbr(int n)
{
    int count;

    count = 0;
    if (n == -2147483648)
    {
        count += ft_put_str("-2147483648");
        return (count);
    }
    if (n < 0)
    {
        count += ft_put_char('-');
        n = -n;
    }
    if (n > 9)
        count += ft_put_nbr(n / 10);
    count += ft_put_char(n % 10 + '0');
    return (count);
}

int ft_put_hex(unsigned int n)
{
    int count;

    count = 0;
    if (n > 15)
        count += ft_put_hex(n / 16);
    if (n % 16 < 10)
        count += ft_put_char(n % 16 + '0');
    else
        count += ft_put_char(n % 16 - 10 + 'a');
    return (count);
}

int    ft_printf(const char *format, ...)
{
    va_list	args;
    int		i;
    int		count;

    va_start(args, format);
    i = 0;
    count = 0;
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'd')
                count += ft_put_nbr(va_arg(args, int));
            else if (format[i] == 's')
                count += ft_put_str(va_arg(args, char *));
            else if (format[i] == 'x')
                count += ft_put_hex(va_arg(args, unsigned int));
            else if (format[i] == '%')
                count += ft_put_char('%');
            else
            {
                count += ft_put_char('%');
                count += ft_put_char(format[i]);
            }   
        }
        else
            count += ft_put_char(format[i]);
        i++;
    }
    va_end(args);
    return (count);
}

// int main(void)
// {
//     int i = -2147483648;
//     char *str = "Hello, World!";
//     ft_printf("This is a number: %d\n", i);
//     ft_printf("This is a string: %s\n", str);
//     ft_printf("This is a hexadecimal: %x\n", i);
//     ft_printf("This is a percent sign: %%\n");
//     return (0);
// }