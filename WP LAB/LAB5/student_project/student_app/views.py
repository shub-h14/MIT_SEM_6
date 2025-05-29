from django.shortcuts import render

# Create your views here.
from .forms import StudentForm

def student_form_view(request):
    form = StudentForm()
    result = ""
    percentage = None

    if request.method == 'POST':
        form = StudentForm(request.POST)
        if form.is_valid():
            data = form.cleaned_data
            total = data['english'] + data['physics'] + data['chemistry']
            percentage = (total / 300) * 100
            result = (
                f"Name: {data['name']}\n"
                f"DOB: {data['dob']}\n"
                f"Address: {data['address']}\n"
                f"Contact: {data['contact']}\n"
                f"Email: {data['email']}\n"
                f"Marks:\n  English: {data['english']}\n  Physics: {data['physics']}\n"
                f"  Chemistry: {data['chemistry']}\n"
                f"Total: {total}/300"
            )

    return render(request, 'student_app/student_form.html', {
        'form': form,
        'result': result,
        'percentage': percentage
    })
