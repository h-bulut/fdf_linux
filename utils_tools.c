#include "fdf.h"

int	handle_sign_and_whitespace(const char *str, int i)
{
	int	sign;

	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (sign);
}

int	process_number(const char *str, int i, int base)
{
	int	result;

	result = 0;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')
		|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * base + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * base + (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * base + (str[i] - 'A' + 10);
		i++;
	}
	return (result);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	i;
	int	sign;

	i = 0;
	sign = handle_sign_and_whitespace(str, i);
	if (base == 16 && str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	result = process_number(str, i, base);
	return (result * sign);
}

int	ft_is_valid_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_strict(const char *str, int *out)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (!ft_is_valid_number(str))
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (0);
		i++;
	}
	*out = (int)(result * sign);
	return (1);
}
