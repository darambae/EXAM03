#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_put_char(char c)
{
	write(1, &c, 1);
	return 1;
}

int	ft_put_str(char *str)
{
	int	count = 0;

	if (!str)
		str = "(null)";	
	while (str[count])
		count += ft_put_char(str[count]);
	return count;
}

int	ft_put_nbr(int nbr)
{
	int	count = 0;

	if (nbr == -2147483648)
		return ft_put_str("-2147483648");
	if (nbr < 0)
	{
		count += ft_put_char('-');
		nbr = -nbr;
	}
	if (nbr > 9)
		count += ft_put_nbr(nbr / 10);
	count += ft_put_char(nbr % 10 + '0');
	return count;
}

int	ft_put_hex(int hex)
{
	int	count = 0;

	if (hex > 15)
		count += ft_put_hex(hex / 16);
	if (hex > 9)
		count += ft_put_char(hex % 16 - 10 + 'a');
	count += ft_put_char(hex % 16 + '0');
	return count;
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int	i = 0;
	int	count = 0;

	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
				count += ft_put_str(va_arg(ap, char *));
			else if (format[i] == 'd')
				count += ft_put_nbr(va_arg(ap, int));
			else if (format[i] == 'x')
				count += ft_put_hex(va_arg(ap, long));
			else if (format[i] == '%')
			{
				count += ft_put_char('%');
				count += ft_put_char(format[i]);
			}
		}
		else
			count += ft_put_char(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

int	main(void)
{
	ft_printf("This is %s / %d / %x / %% / %d\n", "TEST", 42, 42, -2147483648);
	return 0;
}
