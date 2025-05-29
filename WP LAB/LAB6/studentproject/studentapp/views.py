# Create your views here.
from django.shortcuts import render, redirect

def first_page(request):
    subjects = ['Math', 'Physics', 'Chemistry', 'Biology']
    if request.method == 'POST':
        # Save data to session
        request.session['name'] = request.POST.get('name')
        request.session['roll'] = request.POST.get('roll')
        request.session['subject'] = request.POST.get('subject')
        return redirect('second_page')
    return render(request, 'studentapp/firstPage.html', {'subjects': subjects})


def second_page(request):
    # Retrieve data from session
    name = request.session.get('name', '')
    roll = request.session.get('roll', '')
    subject = request.session.get('subject', '')
    return render(request, 'studentapp/secondPage.html', {
        'name': name,
        'roll': roll,
        'subject': subject
    })
