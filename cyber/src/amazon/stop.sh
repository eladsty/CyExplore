 #!/bin/bash
aws ec2 start-instances --instance-ids i-070107834ab273992

public_ip=aws ec2 describe-instances --instance-ids i-070107834ab2 \
        --query 'Reservations[*].Instances[*].PublicDnsName' --output text


AWS_KEY="/home/debian/cs605 data management/assignment6/mumbai instance keys"

ssh -v -i "$AWS_KEY"/mumbai-instance-1.pem\
        ec2-user@$public_ip
        
