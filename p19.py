from datetime import datetime, timedelta

BEGIN_DATE_STR = "1 Jan 1901"
END_DATE_STR = "31 Dec 2000"
DAY = 1
SUNDAY = 6

curr_date = datetime.strptime(BEGIN_DATE_STR, "%d %b %Y")
end_date = datetime.strptime(END_DATE_STR, "%d %b %Y")

count = 0
while curr_date <= end_date:
    if curr_date.day == DAY and curr_date.weekday() == SUNDAY:
        count += 1
    
    curr_date += timedelta(days=1)

print(count)
