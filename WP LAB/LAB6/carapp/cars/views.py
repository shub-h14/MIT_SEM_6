# Create your views here.
from django.shortcuts import render

def home(request):
    manufacturers = ['Toyota', 'Honda', 'Ford', 'BMW', 'Hyundai']
    return render(request, 'cars/home.html', {'manufacturers': manufacturers})

def details(request):
    if request.method == 'POST':
        manufacturer = request.POST.get('manufacturer')
        model = request.POST.get('model')
        return render(request, 'cars/details.html', {
            'manufacturer': manufacturer,
            'model': model
        })
    return render(request, 'cars/home.html')  # fallback
