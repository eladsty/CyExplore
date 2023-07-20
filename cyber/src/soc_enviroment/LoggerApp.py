from logging import getLogger, Formatter
import logging.handlers

def LogToSys(remote_ip):
    # Make the desired format string for Syslog
    LOG_FORMAT = f"%(levelname)s:%(filename)s:%(lineno)d - %(process)d - %(asctime)s - %(message)s"


    # Get the root logger
    logger = getLogger()

    syslogHandler = logging.handlers.SysLogHandler(address=(remote_ip,514))

    # only send logs for warning and above:
    logger.setLevel(logging.WARNING)

    # Set the format string for the handler
    syslogHandler.setFormatter(Formatter(LOG_FORMAT))

    logger.addHandler(syslogHandler)
    logger.info("not a warning")
    logger.warning("a warning!")



LogToSys("192.168.1.36")
logging.warning('a virus! check Desktop')
logging.warning('a worm probably cause this~~ check app2')
logging.warning('permission was changed!')
logging.info('new file has been created')


""" 
in the remote server side which saves the log files:
    sudo tail -f /var/log/syslog
    sudo nano /etc/rsyslog.conf
 
# to recieved UDP log file.
    module(load="imudp")
    input(type="imudp" port="514")
    $template FILENAME,"/var/log/%HOSTNAME%/syslog.log"
    *.* ?FILENAME
    
    sudo systemctl restart rsyslog.service 
    sudo nano /etc/rsyslog.conf
    sudo systemctl reload rsyslog.service 
    sudo tail -f /var/log/syslog
    sudo nano /etc/rsyslog.conf
    sudo tail -f /var/log/syslog




 """