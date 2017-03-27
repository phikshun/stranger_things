Digital Ocean Provisioner Script For Stranger Things Wall
---------------------------------------------------------

Instructions for use:

- Ensure you have Ansible 2.0 or higher installed
- Ensure that you `pip install dopy`
- Export your Digital Ocean API token as DO_API_TOKEN
- Export your Slack API token as SLACK_TOKEN
- Export your Adafruit.io token as ADA_TOKEN

Now run the Ansible playbook:

`ansible-playbook provision.yaml`

Your Adafruit.io MQTT feed will be called 'strangerthings'. Enjoy.
