def format_duration(seconds):
    yy = seconds // 31536000
    dd = seconds % 31536000 // 86400
    hh = seconds % 86400 // 3600
    mm = seconds % 3600 // 60
    ss = seconds % 60
    ans = []
    if yy == 1:
        ans.append("1 year")
    elif yy > 1:
        ans.append(str(yy) + " years")
    if dd == 1:
        ans.append("1 day")
    elif dd > 1:
        ans.append(str(dd) + " days")
    if hh == 1:
        ans.append("1 hour")
    elif hh > 1:
        ans.append(str(hh) + " hours")
    if mm == 1:
        ans.append("1 minute")
    elif mm > 1:
        ans.append(str(mm) + " minutes")
    if ss == 1:
        ans.append("1 second")
    elif ss > 1:
        ans.append(str(ss) + " seconds")

    if len(ans) >= 3:
        ret = ""
        for i in range(len(ans) - 2):
            ret += ans[i] + ", "
        return ret + ans[-2] + " and " + ans[-1]
    elif len(ans) == 2:
        return ans[0] + " and " + ans[1]
    elif len(ans) == 1:
        return ans[0]
    return "now"