from django.shortcuts import render, redirect
from django.http import HttpResponse
import requests

ESP32_IP = "192.168.43.65"
ESP32_URL = f"http://{ESP32_IP}/"

def index(request):
    if request.method == 'POST':
        command = request.POST.get('command')
        print(command)

        if command in ['1', '0']:
            requests.get(ESP32_URL, params={'command': command}, timeout=2)

        return redirect(request.path)

    return render(request, 'index.html')