import threading

class LockGuard:
    def __init__ (self, lock):
        self.lock = lock
        self.lock.acquire ()
    def __del__ (self):
        self.lock.release ()

lock = threading.Lock()

def critical_section ():
    guard = LockGuard (lock)
    print ('Inside critical section ...')

critical_section ()
print ('Between critical sections ...')
critical_section ()
