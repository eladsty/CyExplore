import smtplib
import ssl
from pathlib import Path
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email.utils import COMMASPACE, formatdate
from email import encoders

def SendMail(port, from_addr, to_addr, pwd, file_path ):
    context = ssl.create_default_context()
    subject = "dino"
    body = "this is cool plush"
    message = MIMEMultipart()
    message["From"] = from_addr
    message["To"] = to_addr
    message["Subject"] = subject

    message.attach(MIMEText(body, "plain"))
    with open(file_path, "rb") as file:
        part = MIMEBase("application", "octet-stream")
        part.set_payload(file.read())
    encoders.encode_base64(part)
    part.add_header("Content-Disposition", f"attachment; filename= {file_path}")
    message.attach(part)
    text = message.as_string()
    with smtplib.SMTP_SSL("smtp.gmail.com", port, context=context) as server:
        server.login(from_addr, pwd)
        server.sendmail(from_addr, to_addr, text)



email ="eladgoodname@gmail.com"
password = "plzjcgfarqbhkrrk"
server = "127.0.0.1"
port = 465
file_path = "/home/elad/elad.shem-tov/cyber/src/application_layer_1/ex8/dino.jpeg"
SendMail(port, email, email, password, file_path)
