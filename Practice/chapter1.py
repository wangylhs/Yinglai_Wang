import array
import re

def test():
    num = {
        "one": 1,
        "two": 2
    }
    return num


# print json.dumps(test(), indent=4)

def unique(s):
    l = list(s)
    b_l = [False] * 128
    for x in l:
        if b_l[ord(x)] is True:
            return False
        b_l[ord(x)] = True
    return True

def checkPermutation(s1,s2):
    l1 = list(s1)
    l2 = list(s2)
    if l1.__len__() != l2.__len__():
        return False
    l1.sort()
    l2.sort()
    i = 0
    for x in l1:
        if x != l2[i]:
            return False
        i = i + 1
    return True

str1 = 'Mr John    Smith'
str1 = re.sub(r"[^\w\s]", '', str1)
str1 = re.sub(r"\s+",'%20',str1)

print str1

#print checkPermutation('abcd','djbc')


