#include <stdio.h>
#include <string.h>

#define h2i(CH) (((CH) >= '0' && (CH) <= '9') ? ((CH) - '0') : \
                  (((CH) >= 'a' && (CH) <= 'f') ? ((CH) - 'a' + 10) : \
                   (((CH) >= 'A' && (CH) <= 'F') ? ((CH) - 'A' + 10) : (-1))))

typedef enum
{
    FALSE = -1,
    TRUE = 1
}Boolean;

static Boolean ssh_ipaddr_ipv4_parse(unsigned char *data, const char *str)
{
  int i, value;

  for (i = 0; i < 4; i++)
    {
      if (i != 0)
        {
          if (!*str)
            {
              switch (i)
                {
                case 1:
                  /* Single zero means 0.0.0.0.
                     Other single digit address is invalid. */
                  if (data[0] == 0)
                    {
                      data[1] = data[2] = data[3] = 0;
                      printf("Returning from %d\n", __LINE__);
                      return TRUE;
                    }
                      printf("Returning from %d\n", __LINE__);
                  return FALSE;

                case 2:
                  /* 1.2 -> 1.0.0.2 */
                  data[3] = data[1];
                  data[1] = data[2] = 0;
                      printf("Returning from %d\n", __LINE__);
                  return TRUE;

                case 3:
                  /* 1.2.3 -> 1.2.0.3 */
                  data[3] = data[2];
                  data[2] = 0;
                      printf("Returning from %d\n", __LINE__);
                  return TRUE;

                default:
                  (void) 0;
                }
            }
          else if (*str == '.' && *(str + 1) != '.')
            {
              str++;
            }
          else
            {
                      printf("Returning from %d\n", __LINE__);
              return FALSE;
            }
        }
      for (value = 0; *str >= '0' && *str <= '9'; str++)
        {
          value = 10 * value + *str - '0';
          if (value > 255)
          {
                      printf("Returning from %d\n", __LINE__);
            return FALSE;
          }
        }

      if ((*str && *str != '.' && !(*str >= '0' && *str <= '9')) ||
          (!*str && i == 0))
      {
                      printf("Returning from %d\n", __LINE__);
          return FALSE;
      }

      data[i] = value;
    }

  if (*str)
  {
                      printf("Returning from %d\n", __LINE__);
    return FALSE;
  }

                      printf("Returning from %d\n", __LINE__);
  return TRUE;
}


static Boolean ssh_ipaddr_ipv6_parse(unsigned char *addr, const char *str)
{
  const char          *cp, *start, *next;
  int                 len, right, i;
  unsigned char       out_bytes[4];
  unsigned long       tmp, need_bytes, right_ptr, left_ptr;

  if (addr)
    {
      /* Zero addr */
      memset(addr, 0, 16);
    }

  /* Have we seen a "::" yet? */
  right = 0;
  left_ptr = 0;
  right_ptr = 16;

  start = cp = str;

  /* Look for next ':' delimiter */
  while (*start)
    {
      if ((cp = strchr(start, ':')) != NULL)
        {
          next = cp + 1;
        }
      else
        {
          cp = strchr(start, '\0');
          next = cp;
        }

      len = cp - start;

      if (len == 0)
        {
          if (*next != ':')
            {
              /* printf("ERROR: Empty element\n"); */
                      printf("Returning from %d\n", __LINE__);
              return FALSE;
            }
          need_bytes = 0;
        }

      /* ipv6 'x', 'xx', 'xxx' or 'xxxx' part? */
      else if (len <= 4)
        {
          for (tmp = i = 0; i < len; i++)
            {
              if (h2i(start[i]) == -1)
                {
                  /* printf("ERROR: Invalid character in address\n"); */
                      printf("Returning from %d\n", __LINE__);
                  return FALSE;
                }
              tmp = (tmp << 4) | h2i(start[i]);
              printf("%04lx\n", tmp);
            }

          out_bytes[0] = (unsigned char)((tmp >>  8) & 0xff);
          printf("%08lx - %c\n", (tmp >> 8), out_bytes[0]);
          out_bytes[1] = (unsigned char)((tmp >>  0) & 0xff);
          printf("%08lx - %c\n", (tmp >> 0), out_bytes[1]);

          need_bytes = 2;
        }
      else if (memchr(start, '.', len) != NULL && (len <= 15))
        {
          char buf[16];

          memcpy(buf, start, len);
          buf[len] = '\0';

          if (ssh_ipaddr_ipv4_parse(out_bytes, buf) == FALSE)
                      printf("Returning from %d\n", __LINE__);
            return FALSE;

          need_bytes = 4;
        }

      else
        {
          /* printf("ERROR: Unrecognized address part\n"); */
                      printf("Returning from %d\n", __LINE__);
          return FALSE;
        }

      if ((right_ptr - left_ptr) < need_bytes)
        {
#if 0
          printf("ERROR: Not enough space in output address "
                 "(have %d, required %d)\n",
                 right_ptr - left_ptr, need_bytes);
#endif
                      printf("Returning from %d\n", __LINE__);
          return FALSE;
        }

      if (right)
        {
          if (addr)
            {
              memmove(addr + right_ptr - need_bytes,
                      addr + right_ptr,
                      16 - right_ptr);
              memcpy(addr + 16 - need_bytes, out_bytes, need_bytes);
            }
          right_ptr -= need_bytes;
        }
      else
        {
          if (addr)
            memcpy(addr + left_ptr, out_bytes, need_bytes);
          left_ptr += need_bytes;
        }

      if (*next == ':')
        {
          if (right)
            {
              /* printf("ERROR: Already seen '::'\n"); */
                      printf("Returning from %d\n", __LINE__);
              return FALSE;
            }

          right = 1;
          next++;
        }

      /* Move on to next iteration */
      start = next;
    }

  if ((right_ptr - left_ptr) > 0 && !right)
    {
      /* printf("ERROR: %d unresolved address bytes\n",
         right_ptr - left_ptr); */
                      printf("Returning from %d\n", __LINE__);
      return FALSE;
    }

                      printf("Returning from %d\n", __LINE__);
  return TRUE;
}

int main()
{
    char array[] = "fedc:ba98:7654:3210:fedc:ba98:7654:3210";
    unsigned char addr[16];
    if (TRUE == ssh_ipaddr_ipv6_parse(addr, array))
    {
        printf("The ipv6 address is \n");
        printf("%s\n", addr);
    }
    else
    {
        printf("Cannot parse\n");
    }
}
