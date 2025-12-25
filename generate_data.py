import sys, random
from datetime import date, timedelta

MAX_NAME_LEN = 20
MAX_GROUP_LEN = 7
MIN_AGE = 10
MAX_AGE = 40
MIN_MARK = 1.0
MAX_MARK = 5.0
MIN_DATE = date(1900, 1, 1)
MAX_DATE = date(2025, 12, 31)
DAY_RANGE = (MAX_DATE - MIN_DATE).days
MAX_STREAT_LEN = 20
MAX_HOUSE_FLAT = 100
MIN_COST = 3000
MAX_COST = 50000

NAME_SYMBS = "qwertyiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
GROUP_SYMBS = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!#*-+"
STREAT_SYMBS = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"

GENERATION_FILE = "students.txt"
N = 100000

def gen_str(length, symbs):
    res = ""
    for i in range(length):
        res += random.choice(symbs)
    return res

def gen_address(address_type):
    if (address_type == 1):
        streat_len = random.randint(1, MAX_STREAT_LEN)
        streat = gen_str(streat_len, STREAT_SYMBS)
        house = random.randint(1, MAX_HOUSE_FLAT)
        flat = random.randint(1, MAX_HOUSE_FLAT)
        return f"{streat}\n{house}\n{flat}"
    elif (address_type == 2):
        hostel = random.randint(1, MAX_HOUSE_FLAT)
        room = random.randint(1, MAX_HOUSE_FLAT)
        return f"{hostel}\n{room}"
    streat_len = random.randint(1, MAX_STREAT_LEN)
    streat = gen_str(streat_len, STREAT_SYMBS)
    house = random.randint(1, MAX_HOUSE_FLAT)
    flat = random.randint(1, MAX_HOUSE_FLAT)
    cost = random.randint(MIN_COST, MAX_COST)
    return f"{streat}\n{house}\n{flat}\n{cost}"

n = N if len(sys.argv) == 1 else int(sys.argv[1])
with open(GENERATION_FILE, 'w') as file:
    for i in range(n):
        name_len = random.randint(1, MAX_NAME_LEN)
        group_len = random.randint(1, MAX_GROUP_LEN)

        second_name = gen_str(name_len, NAME_SYMBS)
        first_name = gen_str(name_len, NAME_SYMBS)
        group = gen_str(group_len, GROUP_SYMBS)
        is_male = 'm' if bool(random.getrandbits(1)) else 'f'
        age = random.randint(MIN_AGE, MAX_AGE)
        avg_mark = random.uniform(MIN_MARK, MAX_MARK)
        enter_date = MIN_DATE + timedelta(days=int(random.randint(0, DAY_RANGE)))
        address_type = random.randint(1, 3)
        address = gen_address(address_type)

        file.write(f"{second_name}\n{first_name}\n{group}\n{is_male}\n{age}\n{avg_mark}\n{enter_date.strftime("%d-%m-%Y")}\n{address_type}\n{address}\n")