#let title_page(
  title: "",
  faculty: "",
  author: "",
  supervisor: "",
) = {
  set document(title: title, author: author)
  set page(
    margin: (left: 35mm, right: 25mm, top: 30mm, bottom: 30mm),
    numbering: none,
    number-align: center,
  )

  let body-font = "New Computer Modern"
  let sans-font = "New Computer Modern Sans"

  set text(
    font: body-font, 
    size: 12pt, 
    lang: "cs"
  )
  
  set par(leading: 1em)

  
  // --- Cover ---
  align(center, text(font: sans-font, size: 20pt, "České vysoké učení technické v Praze")) 
  align(center, text(font: sans-font, size: 16pt, faculty))
  
  align(center, image("symbol_cvut_konturova_verze.svg", width: 40%))

  v(3cm)
  align(center, text(font: sans-font, size: 24pt, "XY Plotter"))
  align(center, text(font: sans-font, size: 16pt, "Bakalářská práce"))
  
  v(4cm)

  pad(
    top: 3em,
    right: 15%,
    left: 15%,
    grid(
      columns: 2,
      gutter: 1em,
      strong("Author: "), author,
      strong("Supervisor: "), supervisor,
      // strong("Start Date: "), "startDate",
      // strong("Submission Date: "), submissionDate,
    )
  )
  
  pagebreak()

}
