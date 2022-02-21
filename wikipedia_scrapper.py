import http.client
import re
from pathlib import Path
from queue import Queue

import bs4
from bs4 import SoupStrainer

def get_neighbors(conn, current):
    """
    This function is meant to look at the wikipedia page and retreive all the unique link to travel through.

    Parameters
    ----------
    conn : http.client.HTTPSConnection
        The HTTPS connection in order to reduce the SSL handshake overhead
    
    current: str
        The current webspage to scrape through, in the format '/wiki/....
    """
    conn.request('GET', current)
    html = conn.getresponse().read()

    strainer = SoupStrainer('div', {'id': 'bodyContent'})
    soup = bs4.BeautifulSoup(html, features='lxml', parse_only=strainer)

    links = soup.find_all('a', attrs={'href': re.compile('^/wiki/[a-zA-Z_()0-9-%]+$')})

    l = []

    for link in set(links):
        l.append(link.attrs['href'])

    return l


if __name__ == '__main__':
    conn = http.client.HTTPSConnection('en.wikipedia.org', port=443)

    name_mapping = dict()
    database = dict()

    frontier = Queue()

    start = '/wiki/Cheese'

    frontier.put(start)
    reached = set()
    reached.add(start)

    save_file = 'save4.txt'

    with open(save_file, 'a') as file:
        i = 0

        while not frontier.empty():
            current = frontier.get()

            print(current, i)

            neighbors = get_neighbors(conn, current)

            database[current] = neighbors

            file.write(current.removeprefix('/wiki/') + ',' + str(len(neighbors)) + ',' + ','.join(
                neighbor.removeprefix('/wiki/') for neighbor in neighbors) + '\n')

            if i % 10 == 0:
                file.flush()

                if Path(save_file).stat().st_size / 1e6 > 98:
                    break

            i += 1

            for next in neighbors:
                if next not in reached:
                    frontier.put(next)
                    reached.add(next)
